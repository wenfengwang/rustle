
## ceilやfloorを指定せずに不適切な丸め処理

### 設定

* detector id: `round`
* 重大度: medium

### 説明

算術演算で丸め処理が使用されているかどうかを検出します。方向を指定しない丸め処理は、DeFiで悪用される可能性があります。詳細については、[How to Become a Millionaire, 0.000001 BTC at a Time (neodyme.io)](https://blog.neodyme.io/posts/lending_disclosure/) を参照してください。

注記: **Rustle**は、開発者が特定の目的のために実装した丸め関数については報告しません。

### サンプルコード

```rust
let fee = (amount * fee_rate).round();
```

この例では、契約開発者は `round` を使用して手数料を計算すべきではありません。代わりに、丸めの方向を指定するために `ceil` または `floor` を使用すべきです。
