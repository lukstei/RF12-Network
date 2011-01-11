#ifndef _DEBUG_H_

#ifndef DEBUG
# define DEBUG                 1
# define LOG_LEVEL             0
#endif

#if DEBUG
# define PRELOG()                   Serial.print("> "); 
# define LOG(n, str)                if(n >= LOG_LEVEL) {PRELOG(); Serial.println(str);}
# define LOG2(n, str1, str2)        if(n >= LOG_LEVEL) {PRELOG(); Serial.print(str1); Serial.print(" "); Serial.println(str2);}
# define LOG3(n, str1, str2, str3)  if(n >= LOG_LEVEL) {PRELOG(); Serial.print(str1); Serial.print(" "); Serial.print(str2); Serial.print(" "); Serial.println(str3);}
# define LOGN(n, str, num)          if(n >= LOG_LEVEL) {PRELOG(); Serial.print(str); Serial.print(" "); Serial.println(num, DEC);}
# define LOGN2(n, str, num1, num2)  if(n >= LOG_LEVEL) {PRELOG(); Serial.print(str); Serial.print(" "); Serial.print(num1, DEC); Serial.print(", "); Serial.println(num2, DEC);}
# define LOGC(n, ch)                if(n >= LOG_LEVEL) {Serial.print(ch);}
#else
# define LOG(n, str) 
# define LOG2(n, str1, str2) 
# define LOG3(n, str1, str2, str3) 
# define LOGN(n, str, num)
# define LOGN2(n, str, num1, num2)
# define LOGC(n, ch) 
# define LOGM(n, str, enu)
#endif

#endif