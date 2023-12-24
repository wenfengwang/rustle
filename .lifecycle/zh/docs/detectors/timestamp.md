## 时间戳的依赖

### 配置

* 检测器 ID: `timestamp`
* 严重性: 信息

### 描述

时间戳的依赖关系可能导致被利用，因为它可能被矿工操纵。例如，在彩票合约中，头奖是利用时间戳生成的，这样矿工可能有办法操纵时间戳以获取头奖。

**Rustle** 提供了此检测器，帮助用户通过定位所有`timestamp`的使用来找到不正确的时间戳用法。

### 示例代码

以下是彩票合约的示例。获胜者是利用时间戳生成的，这意味着结果可以被能够控制时间戳的人操纵。

```rust
impl Lottery{
    fn get_winner(&self) -> u32 {
        let current_time = env::block_timestamp();
        let winner_id = self.generate_winner(&current_time);

        winner_id
    }
}