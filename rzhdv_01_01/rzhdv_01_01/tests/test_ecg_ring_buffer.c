#include "ecg_ring_buffer.h"

#include "unity.h"

extern void setUp(void);
extern void tearDown(void);


void test_ecg_ring_buffer_initialization(void)
{
    TEST_ASSERT_EQUAL(0, ecg_ring_buffer_initialization());
}

void test_ecg_ring_buffer_push(void)
{
    ecg_ring_buffer_initialization();
    uint32_t old_current_ecg_push_index = current_ecg_push_index;
    ecg_ring_buffer_push(777);
    TEST_ASSERT_EQUAL(1, current_ecg_push_index - old_current_ecg_push_index);
    TEST_ASSERT_EQUAL(777, ecg_ring_buffer[old_current_ecg_push_index]);
    old_current_ecg_push_index = current_ecg_push_index;
    ecg_ring_buffer_push(999);
    TEST_ASSERT_EQUAL(1, current_ecg_push_index - old_current_ecg_push_index);
    TEST_ASSERT_EQUAL(999, ecg_ring_buffer[old_current_ecg_push_index]);
    old_current_ecg_push_index = current_ecg_push_index;
    ecg_ring_buffer_push(555);
    TEST_ASSERT_EQUAL(1, current_ecg_push_index - old_current_ecg_push_index);
    TEST_ASSERT_EQUAL(555, ecg_ring_buffer[old_current_ecg_push_index]);


    ecg_ring_buffer_initialization();
    int i = 0;
    for(i=1; i<(ECGBUFFERLENGTH - 1); i++)
    {
        ecg_ring_buffer_push(i);
    }
    TEST_ASSERT_EQUAL(ECGBUFFERLENGTH - 2, ecg_ring_buffer[ECGBUFFERLENGTH - 2]);
    TEST_ASSERT_EQUAL(0, current_ecg_pop_index);
    ecg_ring_buffer_push(777);
    TEST_ASSERT_EQUAL(1, current_ecg_pop_index);
    ecg_ring_buffer_push(777);
    TEST_ASSERT_EQUAL(2, current_ecg_pop_index);

}


void test_ecg_ring_buffer_pop(void)
{
    ecg_ring_buffer_initialization();
    ecg_ring_buffer[0] = 333;
    uint32_t aux;
    ecg_ring_buffer_pop(&aux);
    TEST_ASSERT_EQUAL(333, aux);
    TEST_ASSERT_EQUAL(1, current_ecg_pop_index);
    ecg_ring_buffer_pop(&aux);
    TEST_ASSERT_EQUAL(333, aux);
    TEST_ASSERT_EQUAL(1, current_ecg_pop_index);
    ecg_ring_buffer_push(555);
    ecg_ring_buffer_pop(&aux);
    TEST_ASSERT_EQUAL(555, aux);
    TEST_ASSERT_EQUAL(2, current_ecg_pop_index);
    ecg_ring_buffer_push(777);
    ecg_ring_buffer_pop(&aux);
    TEST_ASSERT_EQUAL(777, aux);
    TEST_ASSERT_EQUAL(3, current_ecg_pop_index);
    ecg_ring_buffer_pop(&aux);
    TEST_ASSERT_EQUAL(777, aux);
    TEST_ASSERT_EQUAL(3, current_ecg_pop_index);

}
