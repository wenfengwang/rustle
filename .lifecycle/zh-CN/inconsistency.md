
## 符号不一致问题

### 配置项

* 检测器ID：不一致性
* 严重级别：信息

### 描述

具有相似但略有差异的符号名称可能被错误使用。这类错误手动查找难度大，但可能导致严重后果。

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

在这个例子中，合约应当使用 GAS_FOR_FT_TRANSFER 而非 GAS_FOR_NFT_TRANSFER。这两个常数的值可能会有很大差异，而用于 ft_transfer 的 Gas 可能不足。
