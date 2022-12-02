libcommon = static_library('common',
    'xdgmime.c',
    'xdgmimeglob.c',
    'xdgmimeint.c',
    'xdgmimemagic.c',
    'xdgmimealias.c',
    'xdgmimeparent.c',
    'xdgmimecache.c',
    'xdgmimeicon.c',
    native: true,
)

test_mime = executable('test-mime',
    'test-mime.c',
    link_with: libcommon,
    native: true,
    install: false,
)
meson.override_find_program('test-mime', test_mime)

test_mime_data = executable('test-mime-data',
    'test-mime-data.c',
    link_with: libcommon,
    native: true,
    install: false,
)
meson.override_find_program('test-mime-data', test_mime_data)

print_mime_data = executable('print-mime-data',
    'print-mime-data.c',
    link_with: libcommon,
    native: true,
    install: false,
)
meson.override_find_program('print-mime-data', print_mime_data)
