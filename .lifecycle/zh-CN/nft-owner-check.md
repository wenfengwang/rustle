
## NFT转账过程中缺少检查批准ID

### 配置

* 检测器ID：nft-owner-check
* 严重性：高

### 描述

在[NEP-178](https://github.com/near/NEPs/blob/master/neps/nep-0178.md)的设计中，NFT的所有者可以通过使用指定的接口（即`nft_approve`、`nft_revoke`和`nft_revoke_all`）来批准或撤销批准。这些接口应该实施所有者检查，以确保只有所有者可以调用，否则任何人都可以修改NFT的批准。

### 示例代码

在[near-contract-standards](https://github.com/near/near-sdk-rs/blob/a903f8c44a7be363d960838d92afdb22d1ce8b87/near-contract-standards/src/non_fungible_token/approval/approval_impl.rs)中的代码展示了正确的实现方式。

```rust
// should be implemented for `nft_approve`, `nft_revoke` and `nft_revoke_all`
let owner_id = expect_token_found(self.owner_by_id.get(&token_id));
let predecessor_account_id = env::predecessor_account_id();

require!(predecessor_account_id == owner_id, "Predecessor must be token owner.");
```
