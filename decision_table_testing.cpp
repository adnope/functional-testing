#include <climits>
#include <cstdint>
#include <iostream>
#include <random>

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
    std::cout << "Result = " << result << ", expected: " << expected
              << " [FAILED]\n";
  }
}

int generateRandomP(int min, int max) {
  std::random_device rd;
  std::mt19937 rand(rd());
  std::uniform_int_distribution<int> dist(min, max);
  return dist(rand);
}

void generateTestCases() {
  // Values for p in each C3->C9 condition
  int p3 = generateRandomP(INT_MIN, -1);
  int p4 = generateRandomP(0, 50);
  int p5 = generateRandomP(51, 200);
  int p6 = generateRandomP(201, 2000);
  int p7 = generateRandomP(2001, 8000);
  int p8 = generateRandomP(8001, 10000);
  int p9 = generateRandomP(10001, INT_MAX);
  int test_case_count = 1;
  for (bool eBill : {true, false}) {
    for (int customerType : {1, 2}) {
      for (int p : {p3, p4, p5, p6, p7, p8, p9}) {
        std::cout << "R" << test_case_count++ << ": {" << p << ", " << eBill
                  << ", " << customerType << "}\n";
      }
    }
  }
}

int main() {
  // generateTestCases();

  test(-2086983171, true, 1, -1);  // R1
  test(35, true, 1, 51450);        // R2
  test(62, true, 1, 102900);       // R3
  test(343, true, 1, 861420);      // R4
  test(5450, true, 1, 16352280);   // R5
  test(9940, true, 1, 29948898);   // R6
  test(1520005654, true, 1, -1);   // R7
  test(-2086983171, true, 2, -1);  // R8
  test(35, true, 2, 85750);        // R9
  test(62, true, 2, 157780);       // R10
  test(343, true, 2, 1053990);     // R11
  test(5450, true, 2, 19128130);   // R12
  test(9940, true, 2, 34990851);   // R13
  test(1520005654, true, 2, -1);   // R14
  test(-2086983171, false, 1, -1); // R15
  test(35, false, 1, 52500);       // R16
  test(62, false, 1, 105000);      // R17
  test(343, false, 1, 879000);     // R18
  test(5450, false, 1, 16686000);  // R19
  test(9940, false, 1, 30560100);  // R20
  test(1520005654, false, 1, -1);  // R21
  test(-2086983171, false, 2, -1); // R22
  test(35, false, 2, 87500);       // R23
  test(62, false, 2, 161000);      // R24
  test(343, false, 2, 1075500);    // R25
  test(5450, false, 2, 19518500);  // R26
  test(9940, false, 2, 35704950);  // R27
  test(1520005654, false, 2, -1);  // R28

  return 0;
}
