#include <timer.hpp>


// 1. calculate the expiration that will occur in 7 days
ACTION timer::starttimer(name usern) {
  require_auth(usern);
  print("start the timer, ", name{usern});
  

    user _user(_self, usern.value);
    
    
    auto it = _user.find(usern.value);
    
    if(it == _user.end()){
      it = _user.emplace(usern, [&](auto& new_acc){
        new_acc.usern = usern;
        new_acc.timer = current_time_point();
        new_acc.expiration = current_time_point();
    });
  
  }
  
}


ACTION timer::expiration(name usern){
  require_auth(usern);
  static const uint32_t now = current_time_point().sec_since_epoch();
  static const uint32_t r = now % hours(24).to_seconds();
  static const time_point_sec expire_date = (time_point_sec)(now - r + (7 * hours(24).to_seconds()));
  
  user _user(_self, usern.value);
  
  // start the clock
  auto it = _user.find(usern.value);
     _user.modify(it, get_self(), [&]( auto& new_acc){
        new_acc.expiration = expire_date;
  });
}


ACTION timer::elapsedtime(name usern){
  require_auth(usern);
  
 
  auto itr = _user.find(usern.value);
  
  if(itr->expiration > current_time_point()){
    print("the deadline has passed");
    // reset the clock
   
  }else{
    print("the deadline has not yet passed");
    // missed payments are accummulated
  }
}


// reset the clock
ACTION timer::resettimer(name usern) {
  require_auth(usern);
  
   user _user(_self, usern.value);
  auto itr = _user.find(usern.value);
  
  _user.modify(itr, get_self(), [&]( auto& new_acc){
        new_acc.timer = current_time_point(); 
        new_acc.expiration = current_time_point();
  });
}



