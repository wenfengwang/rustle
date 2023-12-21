
## 乗算の前の除算

### 設定

* 検出器ID: `div-before-mul`
* 重大度: medium

### 説明

`3 / 2 * 6 == 6` のように、乗算の前に除算を行うと、`3 * 6 / 2 == 9` と比較して異なる結果になります。これにより精度損失が発生する可能性があります。

除算の前に乗算を行うことを推奨します。

### サンプルコード

以下は一例です。式 `farm.amount / (farm.end_date - farm.start_date) as u128` は切り捨てられ、精度損失を招く可能性があります。

```rust
// https://github.com/linear-protocol/LiNEAR/blob/fdbacc68c98205cba9f42c130d464ab3114257b6/contracts/linear/src/farm.rs#L125
let reward_per_session =
    farm.amount / (farm.end_date - farm.start_date) as u128 * SESSION_INTERVAL as u128;
```

精度損失を軽減するために、乗算の後に除算を行うことを推奨します。

```rust
let reward_per_session =
    farm.amount * SESSION_INTERVAL as u128 / (farm.end_date - farm.start_date) as u128;
```
