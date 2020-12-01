#include "Sensortest.h"
#include "stm32f1xx_hal.h"
#include <stdint.h>
#include <main.h>
#include <array>
#include <utility>
#include <memory>

extern uint32_t count_tt;

class Sensor_test {
public:
	Sensor_test();
	virtual ~Sensor_test();
	void increment();
	uint32_t count_t;
};

Sensor_test::Sensor_test() {
	// TODO Auto-generated constructor stub

}

Sensor_test::~Sensor_test() {
	// TODO Auto-generated destructor stub
}


void Sensor_test::increment() {
	count_t++;
}

Sensor_test tst;

std::array<Sensor_test, 10> tst_array;

Sensor_test* t = new Sensor_test;

std::shared_ptr<Sensor_test> p = std::make_shared<Sensor_test>();

extern "C" void test_func() {
	tst.increment();
	count_tt = tst.count_t;
	HAL_GPIO_TogglePin(LED1_PIN_GPIO_Port, LED1_PIN_Pin);
	for (std::array<Sensor_test,10>::value_type & t : tst_array) {
		t.count_t++;
	}
	//tst_array[0].count_t++;
	t->count_t++;
	p->increment();
}

