
## 符号不一致问题

### 配置

* 检测器ID：`inconsistency`
* 严重性：信息

### 描述

具有相似但略有差异的名称的符号可能会被误用。这种错误手动发现很困难，但可能导致严重后果。

### 示例代码

```rust
ext::ft_transfer(
    receiver_id,
    U128(amount),
    None,
    token_id,
    1,
    GAS_FOR_NFT_TRANSFER  // 这里应该使用 GAS_FOR_FT_TRANSFER
)
```

在这个示例中，合约应该使用 `GAS_FOR_FT_TRANSFER` 而不是 `GAS_FOR_NFT_TRANSFER`。这两个常数的值可能有很大差异，而为 `ft_transfer` 提供的 gas 可能不足。