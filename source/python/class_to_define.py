class BankAccount:
    def __init__(self, owner, balance=0):
        self.owner = owner
        self.balance = balance

    def deposit(self, amount):
        self.balance += amount
        return self.balance

    def withdraw(self, amount):
        if amount > self.balance:
            raise ValueError("Insufficient funds")
        self.balance -= amount
        return self.balance

    def get_balance(self):
        return self.balance

acct = BankAccount("Alice", 100)
print(f"Owner: {acct.owner}")
print(f"Initial balance: {acct.get_balance()}")

acct.deposit(50)
print(f"After deposit 50: {acct.get_balance()}")

acct.withdraw(30)
print(f"After withdraw 30: {acct.get_balance()}")

try:
    acct.withdraw(500)
except ValueError as e:
    print(f"Error: {e}")

print(f"Final balance: {acct.get_balance()}")
