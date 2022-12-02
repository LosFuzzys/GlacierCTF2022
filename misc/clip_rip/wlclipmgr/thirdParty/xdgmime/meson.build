project('xdgmime', 'c',
    version: '0.0',
    default_options: ['c_std=c99', 'warning_level=1', 'debug=true'],
    meson_version: '>=0.48.0',
)

add_project_arguments(
    '-D_POSIX_C_SOURCE=200809L',
    '-DXDG_PREFIX=xdg_test',
    '-DHAVE_MMAP',
    '-Wmissing-prototypes',
    '-Wno-sign-compare',
    language: 'c',
    native: true,
)

subdir('src')
