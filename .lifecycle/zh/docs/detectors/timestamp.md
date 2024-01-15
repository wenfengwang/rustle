## 时间戳的依赖

### 配置

* 检测器 ID： `timestamp`
* 严重性：提示

### 描述

时间戳依赖可能导致被利用，因为它可能被矿工操纵。例如，在一个彩票合约中，如果头奖是根据时间戳生成的，那么矿工可能会有办法操纵时间戳来赢得头奖。

**Rustle** 提供了此检测器，通过定位 `timestamp` 的所有用法来帮助用户找到不正确的时间戳用法。

### 示例代码

这是一个彩票合约的示例。获胜者是通过时间戳生成的，这意味着结果可能被那些能够控制时间戳的人所操控。

```rust
impl Lottery{
    fn get_winner(&self) -> u32 {
        let current_time = env::block_timestamp();
        let winner_id = self.generate_winner(&current_time);

        winner_id
    }
}
```