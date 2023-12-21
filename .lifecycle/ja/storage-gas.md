
## ストレージ拡張のチェック不足

### Configuration

* detector id: `storage-gas`
* severity: 低

### Description

状態が成長するたびに、拡張をカバーするのに十分なBalanceがあることを確認する必要があります。

### サンプルコード

以下のコードでは、`self.banks`への挿入後にストレージ使用量が増加します。呼び出し元が添付したストレージ料金が十分かどうかを確認するために、増加分をチェックする必要があります。

```rust
let prev_storage = env::storage_usage();

self.banks.insert(&Bank {
    owner: bank.owner,
    balance: bank.balance.0,
});

assert!(
    env::attached_deposit() > ((env::storage_usage() - prev_storage) as u128 * env::storage_byte_cost()),
    "ストレージガスが不足しています"
);
```
