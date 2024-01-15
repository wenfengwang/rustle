
## 一貫性のないシンボル

### 設定

* 検出器ID: `inconsistency`
* 重大度: info

### 説明

似たような名前だが微妙に異なるシンボルは、誤用される可能性があります。このようなエラーは手動で見つけるのは難しいですが、重大な結果を引き起こす可能性があります。

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

このサンプルでは、コントラクトは`GAS_FOR_NFT_TRANSFER`ではなく`GAS_FOR_FT_TRANSFER`を使用すべきです。これら2つの定数は価値が大きく異なる可能性があり、`ft_transfer`のためのガスが不足している可能性があります。
