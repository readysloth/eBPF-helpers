#include <string.h>
#include <stddef.h>

#include <ebpf-helpers.h>

#include "utest.h"

/* Base64 testcases */
/*[[[cog
import random
import base64

import cog


utest_case_fmt = '''
UTEST({namespace}, {test}) {{
  uint8_t bytes_to_conv[] = {{ {bytes_to_conv} }};
  char base64_str_correct[] = "{base64_str_correct}";

  char base64_str[{base64_str_size}] = {{0}};
  size_t written = bytes_to_base64(bytes_to_conv, sizeof(bytes_to_conv), base64_str, sizeof(base64_str));

  if (sizeof(bytes_to_conv) == 0) {{
    ASSERT_EQ(written, 0);
    return;
  }}
  if (sizeof(base64_str) < sizeof(base64_str_correct)) {{
    ASSERT_EQ(written, 0);
    return;
  }}
  ASSERT_EQ(written, sizeof(base64_str_correct));
  ASSERT_STREQ(base64_str_correct, base64_str);
}}
'''

for i in range(100):
  generated_bytes = random.randbytes(random.randrange(0, 4))
  b64_encoded_bytes = base64.b64encode(generated_bytes).decode()
  out_buf_size = len(b64_encoded_bytes) + random.choice([-1, +1]);
  if out_buf_size < 0:
    out_buf_size = 0
  cog.outl(
    utest_case_fmt.format(
      namespace='base64',
      test='less_than_4_' + str(i),
      bytes_to_conv=', '.join([hex(b) for b in generated_bytes]),
      base64_str_correct=b64_encoded_bytes,
      base64_str_size=out_buf_size
    )
  )

for i in range(100):
  generated_bytes = random.randbytes(random.randrange(4, 100))
  b64_encoded_bytes = base64.b64encode(generated_bytes).decode()
  out_buf_size = len(b64_encoded_bytes) + random.choice([-1, +1]);
  if out_buf_size < 0:
    out_buf_size = 0
  cog.outl(
    utest_case_fmt.format(
      namespace='base64',
      test='small_buf_' + str(i),
      bytes_to_conv=', '.join([hex(b) for b in generated_bytes]),
      base64_str_correct=b64_encoded_bytes,
      base64_str_size=out_buf_size
    )
  )

for i in range(100):
  generated_bytes = random.randbytes(random.randrange(1024, 4096))
  b64_encoded_bytes = base64.b64encode(generated_bytes).decode()
  out_buf_size = len(b64_encoded_bytes) + random.choice([-1, +1]);
  if out_buf_size < 0:
    out_buf_size = 0
  cog.outl(
    utest_case_fmt.format(
      namespace='base64',
      test='big_buf_' + str(i),
      bytes_to_conv=', '.join([hex(b) for b in generated_bytes]),
      base64_str_correct=b64_encoded_bytes,
      base64_str_size=out_buf_size
    )
  )

]]]*/
/*[[[end]]]*/

UTEST_MAIN()
