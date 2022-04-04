import testlib


print(testlib.compose(string="42", integer=10))
print(testlib.compose(10, string="42"))
print(testlib.compose(10, "42"))
print(testlib.compose(10))
print(testlib.compose(string="42"))

# print(testlib.compose("10", 42))

# print(help(testlib))
# print(help(testlib.compose))
