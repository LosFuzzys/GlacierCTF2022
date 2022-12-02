xdgmime_target = [
    'xdgmime/src/xdgmime.c',
    'xdgmime/src/xdgmimeglob.c',
    'xdgmime/src/xdgmimeint.c',
    'xdgmime/src/xdgmimemagic.c',
    'xdgmime/src/xdgmimealias.c',
    'xdgmime/src/xdgmimeparent.c',
    'xdgmime/src/xdgmimecache.c',
    'xdgmime/src/xdgmimeicon.c',
  ]

xdgmime = static_library('xdgmime',
    xdgmime_target,
    c_args: [
      '-D_POSIX_C_SOURCE=200809L',
      '-DHAVE_MMAP',
      '-Wmissing-prototypes',
      '-Wno-sign-compare',
      ],
    native: true
    )

