
## ceil や floor を指定せずに不適切な丸め処理

### 設定

* detector id: `round`
* 重大度: medium

### 説明

算術演算で丸めが使用されているかどうかを検出します。方向を指定しない丸めは、DeFiで悪用される可能性があります。詳細は、[How to Become a Millionaire, 0.000001 BTC at a Time (neodyme.io)](https://blog.neodyme.io/posts/lending_disclosure/)を参照してください。

注記: **Rustle**は、開発者が特定の目的で実装した丸め関数については報告しません。

### サンプルコード

```rust
let fee = (amount * fee_rate).round();
```

この例では、契約開発者は`round`を使用して手数料を計算すべきではありません。代わりに、`ceil`または`floor`を使用して丸め方向を明確に指定するべきです。
