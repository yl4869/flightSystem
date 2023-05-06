#include "payment.hpp"

#include <iostream>
Payment::Payment(std::string paymentMethod, double amount,
                 std::string paymentTime, std::string status) {
  this->paymentMethod = paymentMethod;
  this->amount = amount;
  this->paymentTime = paymentTime;
  this->status = status;
  this->refundAmount = 0.0;
}

Payment::Payment(std::string paymentMethod, double amount,
                 std::string paymentTime, std::string status,
                 double refundAmount) {
  this->paymentMethod = paymentMethod;
  this->amount = amount;
  this->paymentTime = paymentTime;
  this->status = status;
  this->refundAmount = refundAmount;

}

void Payment::displayPaymentInfo() {
  std::cout << "Payment Method: " << paymentMethod << std::endl;
  std::cout << "Amount: " << amount << std::endl;
  std::cout << "Payment Time: " << paymentTime << std::endl;
  std::cout << "Status: " << status << std::endl;
  std::cout << "Refund Amount: " << refundAmount << std::endl;
}

void Payment::updateStatus(std::string newStatus) {
  status = newStatus;  // update payment status
}

bool Payment::refund(double amount) {
  if (amount > this->amount - refundAmount) {
    return false;  // not enough amount to refund
  }
  refundAmount += amount;  // update refund amount
  return true;             // refund successful
}

double Payment::getRefundAmount() {
  return refundAmount;  // return refunded amount
}
