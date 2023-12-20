
## 检查NEP接口的完整性

### 配置

* 检测器ID：nep${id}-interface（其中${id}为NEP的ID）
* 严重性：中等

### 描述

[NEP](https://github.com/near/NEPs)代表近端增强提案，它们是对NEAR协议规范和标准所做的一些变更。目前，已有关于FT（代币）、NFT（非同质化代币）、MT（多代币）和存储的NEP，并已列在一张[表格](https://github.com/near/NEPs#neps)中。

要使用这个检测器，你需要在检测器ID中指定NEP的id，例如：

```bash
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep141-interface  # Fungible Token Standard
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep145-interface  # Storage Management
./rustle ~/Git/near-sdk-rs/near-contract-standards -t ~/Git/near-sdk-rs -d nep171-interface  # Non Fungible Token Standard
```

### 示例代码

下面的[example](/examples/nep-interface/)检测器`nep-interface`示例是根据near-contract-standards（NEAR合约标准）修改而来的。
