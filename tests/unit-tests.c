#include <string.h>

#include <ebpf-helpers.h>

#include "utest.h"

/* Base64 testcases */
/*[[[cog
import random
import base64

import cog


utest_case_fmt = '''
UTEST({namespace}, {test}) {{
  char bytes_to_conv[] = {{ {bytes_to_conv} }};
  char base64_str_correct[] = "{base64_str_correct}";

  char base64_str[sizeof(bytes_to_conv) * 4 / 3] = {{0}};
  bytes_to_base64(bytes_to_conv, strlen(bytes_to_conv), base64_str, sizeof(base64_str));
  ASSERT_STREQ(base64_str_correct, base64_str);
}}
'''

for i in range(16):
  generated_bytes = random.randbytes(random.randrange(1, 1024))
  cog.outl(
    utest_case_fmt.format(
      namespace='base64',
      test=i,
      bytes_to_conv=', '.join([hex(b) for b in generated_bytes]),
      base64_str_correct=base64.b64encode(generated_bytes).decode(),
    )
  )

]]]*/
/*[[[end]]]*/

UTEST_MAIN()
