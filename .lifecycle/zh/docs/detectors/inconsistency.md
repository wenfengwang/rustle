## 符号不一致

### 配置

* 检测器 ID： `inconsistency`
* 严重性：信息

### 描述

名称相似但略有不同的符号可能会被误用。这种错误很难手动发现，但可能导致严重的后果。

### 示例代码

```rust
ext::ft_transfer(
    receiver_id,
    U128(amount),
    None,
    token_id,
    1,
    GAS_FOR_NFT_TRANSFER  // should use GAS_FOR_FT_TRANSFER here
)
```

在此示例中，合约应使用 `GAS_FOR_FT_TRANSFER` 而不是 `GAS_FOR_NFT_TRANSFER`。这两个常量的值可能会有很大的差异，而且用于 `ft_transfer` 的 gas 可能不足。