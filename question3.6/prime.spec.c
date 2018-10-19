#include "../bdd-for-c.h"

#include "prime.h"

spec("isPrime(int n)") {
    describe("when input is <= 1") {
        it("should return false") {
            check(isPrime(-1) == false);
            check(isPrime(0) == false);
            check(isPrime(1) == false);
        }
    }

    describe("when input is a prime number") {
        it("should return true") {
            check(isPrime(2) == true);
            check(isPrime(3) == true);
            check(isPrime(5) == true);
            check(isPrime(7) == true);
            check(isPrime(11) == true);
            check(isPrime(13) == true);
            check(isPrime(17) == true);
            check(isPrime(19) == true);
            check(isPrime(23) == true);
            check(isPrime(29) == true);
            check(isPrime(31) == true);
            check(isPrime(37) == true);
            check(isPrime(41) == true);
            check(isPrime(43) == true);
            check(isPrime(47) == true);
            check(isPrime(53) == true);
            check(isPrime(59) == true);
            check(isPrime(67) == true);
            check(isPrime(71) == true);
            check(isPrime(79) == true);
        }
    }

    describe("when input is not a prime number") {
        it("should return false") {
            check(isPrime(2*2) == false);
            check(isPrime(2*3) == false);
            check(isPrime(3*3) == false);
            check(isPrime(3*5) == false);
            check(isPrime(5*5) == false);
            check(isPrime(5*7) == false);
            check(isPrime(7*7) == false);
            check(isPrime(7*11) == false);
            check(isPrime(11*11) == false);
            check(isPrime(11*13) == false);
            check(isPrime(13*13) == false);
            check(isPrime(13*17) == false);
        }
    }
}