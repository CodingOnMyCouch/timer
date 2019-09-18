#include <eosio/eosio.hpp>
#include <eosio/print.hpp>
#include <eosio/system.hpp>
#include <eosio/time.hpp>

using namespace eosio;

CONTRACT timer : public contract {
  public:
    using contract::contract;
    timer(eosio::name receiver, eosio::name code, datastream<const char*> ds):contract(receiver, code, ds),
    _user(receiver, receiver.value){}

  // start the timer
   ACTION starttimer(name usern);
   
   //set the date the deliquency fee will be set and bailout() will occur
   ACTION expiration(name usern);

   
   // if timer has started, check if time has exceeded 7 days
   // send an alert when the timer has gone past seven days
   ACTION elapsedtime(name usern);
   
   ACTION resettimer(name user);
   // reset the timer 
   // 1. when a repayment has been made
   // 2. when the 7 days has been expired
   // reset the timer after (1)
   // reset timer after (2)
  
  //private:
    TABLE user_t {
      name usern;
      eosio::time_point_sec timer;
      eosio::time_point_sec expiration;
      //uint32_t timer;
      uint64_t primary_key()const { return usern.value; }
      //eosio::time_point_sec expires_at() const { return expiration; }
    };
    typedef eosio::multi_index<"users"_n, user_t> user;
  
    user _user;
};

EOSIO_DISPATCH(timer, (starttimer)(expiration)(elapsedtime)(resettimer));

