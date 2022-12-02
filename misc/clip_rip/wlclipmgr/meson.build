project('wlclipmgr', 'cpp', 'c',
    default_options: [
      'cpp_std=c++20',
      'c_std=c99',
      'warning_level=1',
      'debug=true'
      ]
  )

subdir('thirdParty') # declares xdgmime

cc = meson.get_compiler('c')
cpp = meson.get_compiler('cpp')
lprocps = cc.find_library('procps')
lgpgme = cpp.find_library('gpgmepp')
lgpg_error = cpp.find_library('gpg-error')

source_files = [
  'main.cpp',
  'clipboard.cpp',
  'procblock.cpp',
  'gpgmeinterface.cpp',
  ]

wlclipmgr = executable(
  meson.project_name(),
  source_files,
  link_with : [xdgmime],
  dependencies: [
    lprocps,
    lgpgme,
    lgpg_error,
    #dependency('magic_enum'),
    #dependency('msgpack-cxx'),
    ],
  native: true
  )
