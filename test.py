from cs50 import SQL

db = SQL("sqlite:///test.db")

db.execute("CREATE TABLE IF NOT EXISTS orders (id INTEGER, symbol TEXT NOT NULL, shares INTEGER NOT NULL, PRIMARY KEY(id))")

owns = {}

# [{'symbol': 'NFLX', 'shares': 3}]
query = db.execute("SELECT symbol, shares FROM orders WHERE id = 1")

for q in query:
    symbol = q["symbol"] # 'NFLX'
    shares = q["shares"] # 3
    owns[symbol] = owns.setdefault(symbol, 0) + shares

# {'NFLX': 3}
print(owns)