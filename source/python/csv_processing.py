import csv
import io

data = """name,age,score
Alice,30,85
Bob,25,92
Charlie,35,78
Diana,28,95
Eve,32,88"""

reader = csv.DictReader(io.StringIO(data))
rows = list(reader)
high_scorers = [r for r in rows if int(r["score"]) >= 85]
avg = sum(int(r["score"]) for r in high_scorers) / len(high_scorers)
print(f"High scorers (>=85): {len(high_scorers)}")
for r in high_scorers:
    print(f"  {r['name']}: {r['score']}")
print(f"Average score: {avg:.1f}")
