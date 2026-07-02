import os

type
  Config* = object
    file*: string
    output*: string
    showTempFiles*: bool

proc defaultConfig(): Config =
  Config(output: "out", showTempFiles: false)

proc parseArgs*(): Config =
  var cfg = defaultConfig()

  if paramCount() < 1:
    quit("usage: boron <file> [-o output] [--showtempfiles]")

  cfg.file = paramStr(1)

  var i = 2
  while i <= paramCount():
    let arg = paramStr(i)

    case arg
    of "-o":
      inc i
      if i <= paramCount():
        cfg.output = paramStr(i)

    of "--showtempfiles":
      cfg.showTempFiles = true

    else:
      discard

    inc i

  cfg