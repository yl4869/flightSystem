#include <string>
#ifndef __PAYMENT_HPP
#define __PATMENT_HPP
class Payment {
 public:
  std::string paymentMethod;
  double amount;
  std::string paymentTime;
  std::string status;
  double refundAmount;

  Payment(std::string paymentMethod, double amount, std::string paymentTime,
          std::string status);

  Payment(std::string paymentMethod, double amount, std::string paymentTime,
          std::string status, double refundAmount);



  void displayPaymentInfo();

  void updateStatus(std::string newStatus);

  bool refund(double amount);

  double getRefundAmount();
};
#endif  // !PAYMENT_HPP
