
## 符号不一致

### 配置

* 检测器 ID：`inconsistency`
* 严重性：info

### 描述

名称相似但略有差异的符号可能会被误用。这种错误手动发现很困难，但可能导致严重后果。

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

在这个示例中，合约应该使用 `GAS_FOR_FT_TRANSFER` 而不是 `GAS_FOR_NFT_TRANSFER`。这两个常量的值可能差异很大，而且为 `ft_transfer` 提供的 Gas 可能不足。
