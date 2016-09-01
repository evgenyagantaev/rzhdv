#include "frame_ring_buffer.h"

#include "unity.h"

extern void setUp(void);
extern void tearDown(void);

void test_frame_ring_buffer_initialization(void)
{
    TEST_ASSERT_EQUAL(0, frame_ring_buffer_initialization());
}

void test_frame_ring_buffer_push(void)
{
    configure_adas1000();
    frame_ring_buffer_initialization();
    read_frame(primary_buffer);
    uint32_t old_push_index = current_push_index;
    uint32_t old_pop_index = current_pop_index;
    TEST_ASSERT_EQUAL(0, frame_ring_buffer_push(primary_buffer, COLUMNS));
    TEST_ASSERT_EQUAL(old_push_index + 1, current_push_index);
    TEST_ASSERT_EQUAL(old_pop_index, current_pop_index);
    int i;
    for(i=0;i<(RAWS-2);i++)
        frame_ring_buffer_push(primary_buffer, COLUMNS);
    TEST_ASSERT_EQUAL(old_push_index + RAWS - 1, current_push_index);
    TEST_ASSERT_EQUAL(old_pop_index, current_pop_index);
    TEST_ASSERT_EQUAL(0, overflow_flag);
    frame_ring_buffer_push(primary_buffer, COLUMNS);
    TEST_ASSERT_EQUAL(old_push_index + RAWS, current_push_index);
    TEST_ASSERT_EQUAL(old_pop_index + 1, current_pop_index);
    TEST_ASSERT_EQUAL(1, overflow_flag);

}

void test_frame_ring_buffer_pop(void)
{

    int i;

    configure_adas1000();
    frame_ring_buffer_initialization();
    read_frame(primary_buffer);

    for(i=0;i<(RAWS);i++)
        frame_ring_buffer_push(primary_buffer, COLUMNS);
    TEST_ASSERT_EQUAL(1, overflow_flag);
    frame_ring_buffer_pop(secondary_buffer, COLUMNS);
    TEST_ASSERT_EQUAL(0, overflow_flag);
    for(i=0; i<COLUMNS; i++)
        TEST_ASSERT_EQUAL(primary_buffer[i], secondary_buffer[i]);

    configure_adas1000();
    frame_ring_buffer_initialization();

    int j; int summ = 0;
    for(j=0; j<COLUMNS; j++)
    {
        summ += secondary_buffer[j];
    }
    TEST_ASSERT_EQUAL(COLUMNS, summ);
    TEST_ASSERT_EQUAL(0, current_pop_index);
    frame_ring_buffer_pop(secondary_buffer, COLUMNS);
    TEST_ASSERT_EQUAL(0, current_pop_index);
    frame_ring_buffer_push(primary_buffer, COLUMNS);
    frame_ring_buffer_pop(secondary_buffer, COLUMNS);
    TEST_ASSERT_EQUAL(1, current_pop_index);
    summ = 0;
    for(j=0; j<COLUMNS; j++)
    {
        summ += primary_buffer[j];
    }
    TEST_ASSERT_EQUAL(0, summ);
    for(j=0; j<COLUMNS; j++)
    {
        primary_buffer[j] = 1;
    }
    frame_ring_buffer_pop(secondary_buffer, COLUMNS);
    TEST_ASSERT_EQUAL(1, current_pop_index);
    summ = 0;
    for(j=0; j<COLUMNS; j++)
    {
        summ += secondary_buffer[j];
    }
    TEST_ASSERT_EQUAL(0, summ);
    frame_ring_buffer_push(primary_buffer, COLUMNS);
    frame_ring_buffer_pop(secondary_buffer, COLUMNS);
    TEST_ASSERT_EQUAL(2, current_pop_index);
    summ = 0;
    for(j=0; j<COLUMNS; j++)
    {
        summ += secondary_buffer[j];
    }
    TEST_ASSERT_EQUAL(COLUMNS, summ);
}
