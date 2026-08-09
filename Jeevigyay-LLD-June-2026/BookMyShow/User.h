#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
  User(std::string username, std::string password)
  {
    m_sUsername = username;
    m_sPassword = password;
  }

private:
  std::string m_sUsername;
  std::string m_sPassword;
};

#endif // USER_H