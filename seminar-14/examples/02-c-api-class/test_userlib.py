from userlib import UserPyClass as User

default_user = User()
assert default_user.get_full_name() == " "

other_user = User(first_name="John",
                  last_name="Doe",
                  age=42)
assert other_user.get_full_name() == "John Doe"
