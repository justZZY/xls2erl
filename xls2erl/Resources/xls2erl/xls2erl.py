# -*- coding: utf-8 -*-
import os, sys, xlrd, codecs, json
from optparse import OptionParser


def try_int(f):
    if isinstance(f, float) and (int(f) == f):
        return int(f)
    return f


def maybe_syntax_check(spec, row, col, key, val):
    if spec["syntax"] != "on": return
    if isinstance(val, float): return
    if isinstance(val, int): return
    cmd = 'erl -noshell -eval " %s " -s init stop'  \
            % val.replace('"', '\\"')
    if 0 == os.system(cmd): return
    Message = "\nrow: %d\ncol: %d\nkey: %s\nval: %s" \
            % (row + 1, col + 1, key, val)
    raise ValueError(Message)


def pydict_to_erlmap(d):
    if not isinstance(d, dict): return "%s" % d
    l = ["%s => %s" % (k, pydict_to_erlmap(v)) \
                for (k, v) in sorted(d.items())]
    return "#{" + ", ".join(l) + "}"


def deep_setitem(d, ks, v):
    pd, pk = None, None
    for k in ks.split('.'):
        if not isinstance(d, dict):
            pd[pk] = d = {}
        pd, pk, d = d, k, d.get(k)
    pd[pk] = v


def handle_row(spec, table, cols, row):
    d = {}
    for col in cols:
        key = table.cell_value(spec["label"], col)
        val = try_int(table.cell_value(row, col))
        if val not in ['']:
            deep_setitem(d, key, val)
            maybe_syntax_check(spec, row, col, key, val)
    primval = d[spec["primkey"]]
    return "{%s, %s}." % (primval, pydict_to_erlmap(d))


def handle_sheet(spec):
    workbook = xlrd.open_workbook(spec["workbook"])
    table = workbook.sheet_by_name(spec["sheet"])
    cols = [col for col in range(table.ncols) \
            if table.cell_value(spec["label"], col)]
    with codecs.open(spec["output"], "w",  encoding="utf-8") as ofile:
        for row in range(spec["begin"], table.nrows):
            ofile.write(handle_row(spec, table, cols, row) + "\n")


if __name__ == "__main__":
    usage = """usage: %prog [options]"""
    parser = OptionParser(usage=usage)
    parser.add_option("--specs")
    (options, args) = parser.parse_args()
    with codecs.open(options.specs, "r",  encoding="utf-8") as sfile:
        specdict, command = json.loads(sfile.read()), args[0]
        if command == "all":
            speclist = list(specdict.values())
        else:
            speclist = [specdict[command]]
        for spec in speclist:
            spec["label"] -= 1
            spec["begin"] -= 1
            handle_sheet(spec)

