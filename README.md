# NSYSU Algorithm

## 作業目的
4 個作業分別利用不同演算法來解決 TSP 問題，並比較其效率、準確率。

## 作業清單
| 作業 | 演算法 |
|:---:|:---:|
|  HW1  | 暴力法 Exhaustive |
|  HW2  | 貪心法 Greedy |
|  HW3  | 動態規劃 Dynamic Programming |
|  HW4  | 蟻群演算法 Ant Colony Optimization |
| Bonus | Elastic Net |

## 執行程式

### main
```sh
# Compilation
~/HW?> mingw32-make

# Execution
~/HW?> main [-i INPUT] [-o OUTPUT] [-n Name] [-a ANS] [-p]
```

### plot
```sh
~/HW?> python plot.py [-f FILENAME] [-d DATA] [-n NAME]
```

### Execution Script
直接測試 3 個給定的測資
```sh
~/HW?> ./script.cmd
```

---
> Environment: Windows 11, clang version 19.1.2, Python 3.12.5