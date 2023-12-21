
## 一貫性のないシンボル

### 設定

* 検出器ID: `inconsistency`
* 重大度: 情報

### 説明

名前が似ているがわずかに異なるシンボルは、誤用される可能性があります。このようなエラーは手動で見つけるのは困難ですが、重大な結果を招く可能性があります。

### サンプルコード

```rust
ext::ft_transfer(
    receiver_id,
    U128(amount),
    None,
    token_id,
    1,
    GAS_FOR_NFT_TRANSFER  // ここではGAS_FOR_FT_TRANSFERを使用すべきです
)
```

このサンプルでは、コントラクトは `GAS_FOR_NFT_TRANSFER` ではなく `GAS_FOR_FT_TRANSFER` を使用すべきです。これら2つの定数は価値が大きく異なる可能性があり、`ft_transfer` のためのガスが不足している可能性があります。
