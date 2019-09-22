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

 
   ACTION starttimer(name usern);
   
   ACTION expiration(name usern);

   ACTION elapsedtime(name usern);
   
   ACTION resettimer(name user);
  
  
  //private:
    TABLE user_t {
      name usern;
      eosio::time_point_sec timer;
      eosio::time_point_sec expiration;
      
      uint64_t primary_key()const { return usern.value; }
      
    };
    typedef eosio::multi_index<"users"_n, user_t> user;
  
    user _user;
};

EOSIO_DISPATCH(timer, (starttimer)(expiration)(elapsedtime)(resettimer));

