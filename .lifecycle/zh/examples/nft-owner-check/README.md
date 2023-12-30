
# `nft-owner-check`检测器的示例

此示例基于[near-contract-standards](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/approval/approval_impl.rs)的实现。但是，函数[`nft_revoke_all`](src/lib.rs#L171)中的所有者检查已被移除。由于任何人都可以调用此函数来撤销对NFT的所有授权，因此该接口将变得不安全。
