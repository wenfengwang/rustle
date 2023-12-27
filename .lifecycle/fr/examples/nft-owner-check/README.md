
# Exemple du détecteur `nft-owner-check`

Cet exemple est basé sur l'implémentation des [near-contract-standards](https://github.com/near/near-sdk-rs/blob/63ba6ecc9439ec1c319c1094d581653698229473/near-contract-standards/src/non_fungible_token/approval/approval_impl.rs). Toutefois, la vérification du propriétaire dans la fonction [`nft_revoke_all`](src/lib.rs#L171) a été retirée. L'interface deviendra non sécurisée car n'importe qui pourra appeler cette fonction pour révoquer toutes les approbations du NFT.
