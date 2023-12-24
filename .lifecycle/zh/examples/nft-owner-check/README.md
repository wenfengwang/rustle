# 检测器示例 `nft-owner-check`

该示例基于[近合同标准](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/approval/approval_impl.rs)的实现。然而，函数 [`nft_revoke_all`](src/lib.rs#L171) 的所有者检查被移除。这将导致接口变得不安全，因为任何人都可以调用此函数来撤销对 NFT 的所有批准。