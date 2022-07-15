import pandas as pd

day1 = pd.read_csv("day1.csv")
day2 = pd.read_csv("day2.csv")
print(day1.head())
day1["Username"].map(lambda x: str(x))
day2["Username"].map(lambda x: str(x))
dct1 = day1.to_dict(orient="index")
dct2 = day2.to_dict(orient="index")
rows = {}
for k, v in dct1.items():
    rows[k] = {**v, **dct2[k]}
    sm = v["Global"] + dct2[k]["Global"]
    print(sm)
    rows[k]["score"] = sm
cmb = pd.DataFrame.from_dict(rows, orient="index")
cmb.sort_values(by=["score"], ascending=False)
cmb.to_csv("combined.csv")
#day1["Username"].astype(pd.dtype.string)
#day2["Username"].astype(pd.dtype.string)

print(day1.dtypes)
#day1.join(day2, on="Username")
#day1.to_csv("combined_ranking.csv")