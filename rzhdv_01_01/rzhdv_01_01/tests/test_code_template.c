// here is a unit's under test interface
//#include "ProductionCode.h"

#include "unity.h"

extern void setUp(void);
extern void tearDown(void);

void test_some_function(void)
{
  /* All of these should pass */
  TEST_ASSERT_EQUAL(3, 2);
}



