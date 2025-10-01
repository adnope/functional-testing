#include <climits>
#include <cstdint>
#include <iostream>
#include <vector>

int64_t calculateElectricityBill(int p, bool eBill, int customerType) {
  if (p < 0 || p > 10000) {
    std::cout << "Invalid input" << '\n';
    return -1;
  }
  int64_t bill = 0;
  if (customerType == 1) {
    if (p >= 0 && p <= 50) {
      bill = p * 1500L;
    } else if (p >= 51 && p <= 200) {
      bill = (50 * 1500L) + ((p - 50) * 2500L);
    } else if (p > 200) {
      bill = (50 * 1500L) + (150 * 2500L) + ((p - 200) * 3000L);
    }
  } else if (customerType == 2) {
    if (p >= 0 && p <= 50) {
      bill = p * 2500L;
    } else if (p >= 51 && p <= 200) {
      bill = (50 * 2500L) + ((p - 50) * 3000L);
    } else if (p > 200) {
      bill = (50 * 2500L) + (150 * 3000L) + ((p - 200) * 3500L);
    }
  }

  // 2% discount
  if (eBill) {
    bill = bill * 98 / 100;
  }

  // 3% surcharge
  if (p > 2000) {
    bill = bill * 103 / 100;
  }

  if (p > 8000) {
    std::cout << "Warning: Unusually high electricity consumption!" << '\n';
  }

  return bill;
}

void test(int p, bool eBill, int customerType, int64_t expected) {
  int64_t result = calculateElectricityBill(p, eBill, customerType);
  std::cout << "[TESTCASE p=" << p << ", eBill=" << eBill
            << ", customerType=" << customerType << "] ";
  if (result == expected) {
    std::cout << "Result = " << result << " [PASSED]\n";
  } else {
    std::cout << "Result = " << result << ", expected: " << expected << " [FAILED]\n";
  }
}

int main() {
  std::vector<int> p_values = {INT_MIN, -50, -2, -1, 0, 1, 24, 49, 50, 51, 52, 125, 199, 200, 201, 202, 1000, 1999, 2000, 2001, 2002, 5000, 7999, 8000, 8001, 8002, 9000, 9999, 10000, 10001, 10002, 50000, INT_MAX};
  
  // Expected results for test cases
  // eBill = false, customerType = 1
  std::vector<int64_t> expected_01 = {-1, -1, -1, -1, 0, 1500, 36000, 73500, 75000, 77500, 80000, 262500, 447500, 450000, 453000, 456000, 2850000, 5847000, 5850000, 6028590, 6031680, 15295500, 24562410, 24565500, 24568590, 24571680, 27655500, 30742410, 30745500, -1, -1, -1, -1};

  // eBill = false, customerType = 2
  std::vector<int64_t> expected_02 = {-1, -1, -1, -1, 0, 2500, 60000, 122500, 125000, 128000, 131000, 350000, 572000, 575000, 578500, 582000, 3375000, 6871500, 6875000, 7084855, 7088460, 17896250, 28707645, 28711250, 28714855, 28718460, 32316250, 35917645, 35921250, -1, -1, -1, -1};

  // eBill = true, customerType = 1 
  std::vector<int64_t> expected_11 = {-1, -1, -1, -1, 0, 1470, 35280, 72030, 73500, 75950, 78400, 257250, 438550, 441000, 443940, 446880, 2793000, 5730060, 5733000, 5908018, 5911046, 14989590, 24071161, 24074190, 24077218, 24080246, 27102390, 30127561, 30130590, -1, -1, -1, -1};

  // eBill = true, customerType = 2
  std::vector<int64_t> expected_12 = {-1, -1, -1, -1, 0, 2450, 58800, 120050, 122500, 125440, 128380, 343000, 560560, 563500, 566930, 570360, 3307500, 6734070, 6737500, 6943157, 6946690, 17538325, 28133492, 28137025, 28140557, 28144090, 31669925, 35199292, 35202825, -1, -1, -1, -1};

  for (size_t i = 0; i < p_values.size(); ++i) {
    test(p_values[i], false, 1, expected_01[i]);
    test(p_values[i], false, 2, expected_02[i]);
    test(p_values[i], true, 1, expected_11[i]);
    test(p_values[i], true, 2, expected_12[i]);
  }

  return 0;
}
