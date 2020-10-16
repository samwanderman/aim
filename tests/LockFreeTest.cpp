/*
 * LockFreeTest.cpp
 *
 *  Created on: 16.10.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include <cstdint>
#include <atomic>
#include <cstdio>

int main() {
	printf("Is lock free uint8_t\t\t: %s\r\n", std::atomic<uint8_t>().is_lock_free() ? "yes" : "no");
	printf("Is lock free uint8_t*\t\t: %s\r\n", std::atomic<uint8_t*>().is_lock_free() ? "yes" : "no");
	printf("Is lock free int8_t\t\t: %s\r\n", std::atomic<int8_t>().is_lock_free() ? "yes" : "no");
	printf("Is lock free int8_t*\t\t: %s\r\n", std::atomic<int8_t*>().is_lock_free() ? "yes" : "no");
	printf("Is lock free uint16_t\t\t: %s\r\n", std::atomic<uint16_t>().is_lock_free() ? "yes" : "no");
	printf("Is lock free uint16_t*\t\t: %s\r\n", std::atomic<uint16_t*>().is_lock_free() ? "yes" : "no");
	printf("Is lock free int16_t\t\t: %s\r\n", std::atomic<int16_t>().is_lock_free() ? "yes" : "no");
	printf("Is lock free int16_t*\t\t: %s\r\n", std::atomic<int16_t*>().is_lock_free() ? "yes" : "no");
	printf("Is lock free uint32_t\t\t: %s\r\n", std::atomic<uint32_t>().is_lock_free() ? "yes" : "no");
	printf("Is lock free uint32_t*\t\t: %s\r\n", std::atomic<uint32_t*>().is_lock_free() ? "yes" : "no");
	printf("Is lock free int32_t\t\t: %s\r\n", std::atomic<int32_t>().is_lock_free() ? "yes" : "no");
	printf("Is lock free int32_t*\t\t: %s\r\n", std::atomic<int32_t*>().is_lock_free() ? "yes" : "no");
	printf("Is lock free uint64_t\t\t: %s\r\n", std::atomic<uint64_t>().is_lock_free() ? "yes" : "no");
	printf("Is lock free uint64_t*\t\t: %s\r\n", std::atomic<uint64_t*>().is_lock_free() ? "yes" : "no");
	printf("Is lock free int64_t\t\t: %s\r\n", std::atomic<int64_t>().is_lock_free() ? "yes" : "no");
	printf("Is lock free int64_t*\t\t: %s\r\n", std::atomic<int64_t*>().is_lock_free() ? "yes" : "no");
	printf("Is lock free float\t\t: %s\r\n", std::atomic<float>().is_lock_free() ? "yes" : "no");
	printf("Is lock free float*\t\t: %s\r\n", std::atomic<float*>().is_lock_free() ? "yes" : "no");
	printf("Is lock free double\t\t: %s\r\n", std::atomic<double>().is_lock_free() ? "yes" : "no");
	printf("Is lock free double*\t\t: %s\r\n", std::atomic<double*>().is_lock_free() ? "yes" : "no");
	printf("Is lock free bool\t\t: %s\r\n", std::atomic<bool>().is_lock_free() ? "yes" : "no");
	printf("Is lock free bool*\t\t: %s\r\n", std::atomic<bool*>().is_lock_free() ? "yes" : "no");

	return 0;
}
