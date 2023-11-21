# Vitis HLS Benchmark

- 小規模な回路をHLS合成とVivado合成するスクリプト
- タイミングはメットしません
- 小規模な回路なのでシングルコア性能に依存しそう

## 実行

```
$ bash ./benchmark.sh
```

- benchmark.shの中のvitis_hlsのパスを適宜変更すること。
- 秒数が整数で出力されます。

## ベンチマーク

|    Platform   |Mem|Vitis HLS|Vivado|
|:-------------:|:-:|:-:|:-:|
|Intel i9-12900K|128GB| 14s | 260s |
|Apple M2 with Rosetta2 | 24GB |18s | 375s |
