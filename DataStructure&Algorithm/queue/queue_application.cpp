#include "queue_application.h"

using namespace ring_queue;

enum {
	SEED = 1234,
	PRODUCE_COUNT = 10,
	CONSUME_COUNT = 5
};
static_assert(PRODUCE_COUNT > CONSUME_COUNT);

static std::atomic_flag s_is_locked = ATOMIC_FLAG_INIT;

static void produce(ring_queue_t<int>* p_buffer)
{
	assert(p_buffer != nullptr);

	while (s_is_locked.test_and_set()) {
		// lock
	}

	printf("produce: ");
	for (int i = PRODUCE_COUNT; i > 0; --i) {
		const int input = rand() % 10;

		enqueue(p_buffer, input);
		printf("%d ", input);
	}
	printf("\ncount: %lld\n", p_buffer->count);

	s_is_locked.clear();
}

static void consume(ring_queue_t<int>* p_buffer)
{
	assert(p_buffer != nullptr);

	while (s_is_locked.test_and_set()) {
		// lock
	}

	if (is_empty(p_buffer)) {
		goto UNLOCK;
	}

	printf("consume: ");
	for (int i = CONSUME_COUNT; i > 0; --i) {
		const int value = dequeue(p_buffer);
		printf("%d ", value);
	}
	printf("\ncount: %lld\n", p_buffer->count);

UNLOCK:
	s_is_locked.clear();
}

void queue_application::simulate_producer_consumer()
{
	srand(SEED);

	printf("--------start--------\n");
	ring_queue_t<int> buffer = create<int>(PRODUCE_COUNT);
	{
		produce(&buffer);

		std::thread produce_threads[CONSUME_COUNT];
		std::thread consume_threads[PRODUCE_COUNT];

		int i;
		for (i = 0; i < CONSUME_COUNT; ++i) {
			produce_threads[i] = std::thread(produce, &buffer);
			consume_threads[i] = std::thread(consume, &buffer);
		}

		for (; i < PRODUCE_COUNT; ++i) {
			consume_threads[i] = std::thread(consume, &buffer);
		}

		for (i = 0; i < CONSUME_COUNT; ++i) {
			produce_threads[i].join();
			consume_threads[i].join();
		}

		for (; i < PRODUCE_COUNT; ++i) {
			consume_threads[i].join();
		}
	}
	printf("---------end---------\n");

	delete_ring_queue(&buffer);
}
