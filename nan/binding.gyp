{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cpp" ],
      "include_dirs": [ "<!(node -e \"require('nan')\")" ],
      "conditions": [
          ['OS=="mac"', {
              'xcode_settings': {
                  'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
               }
          }]
      ]
    }
  ]
}
