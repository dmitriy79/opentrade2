#ifndef ADAPTERS_THINKTRADER_PB_PB_H_
#define ADAPTERS_THINKTRADER_PB_PB_H_

#include "opentrade/exchange_connectivity.h"

// http://www.thinktrader.net/, 迅投
class PB : public opentrade::ExchangeConnectivityAdapter {
 public:
  void Start() noexcept override;
  void Stop() noexcept override { connected_ = 0; }
  std::string Place(const opentrade::Order& ord) noexcept override;
  std::string Cancel(const opentrade::Order& ord) noexcept override;

  void LoopAction();
  void Loop();

 private:
  struct Order {
    double px;
    int qty;
    std::string mode;
    std::string symbol;
    std::string channel;
  };
  std::unordered_map<int64_t, Order> orders_;
  std::unordered_set<int64_t> pending_cancels_;
  std::unordered_set<std::string> trades_readed_;
  std::unordered_map<int64_t, std::string> status_;
  int interval_ = 1000;  // ms
  std::string dir_;
  int channels_ = 1;
};

#endif  // ADAPTERS_THINKTRADER_PB_PB_H_
