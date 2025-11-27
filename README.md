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

### **main**
| 參數 | 用途 |
|:---|:---|
| `-i INPUT`   | 設定輸入檔案 |
| `-o OUTPUT`  | 設定輸出檔案 |
| `-n Name`    | 設定測試項目名稱，預設為 `Custom Test` |
| `-a ANS`     | 設定正確答案檔案 (選用) |
| `-p`         | 是否繪製路徑，預設不列印 (選用) |

```sh
> main [-i INPUT] [-o OUTPUT] [-n Name] [-a ANS] [-p]
```

```sh
# Compilation
~/HW?> mingw32-make

# Execution
~/HW?> main.exe -i data/dt1/point.txt -o ans_dt1 -a data/dt1/ans.txt -n "Test Case 1" -p
```

### **plot**
| 參數 | 用途 |
|:---|:---|
| `-f FILENAME` | 設定 TSP 輸出檔案名稱 |
| `-d DATA`     | 設定輸入檔案|
| `-n NAME`     | 設定測試項目名稱 |
```sh
> python plot.py [-f FILENAME] [-d DATA] [-n NAME]
```
```sh
~/HW?> python plot.py -f ans_dt1 -d data/dt1/point.txt -n "Test Case 1"
```

### Execution Script
直接測試 3 個給定的測資
```sh
~/HW?> ./script.cmd
```

---
> Environment: Windows 11, gcc version 13.2.0, Python 3.12.5