
const redeem = async () => {
    let code = $("input[name=voucher]").value;
    let voucher = {code: code};
    let res = await graphql(`
        mutation($voucher: JSON!) { 
          redeem(voucher: $voucher) { 
            coins
            message
          } 
        }
        `, {
      voucher: voucher
    });
  
    if (res.errors) {
      alert('could not redeem code ' + res.errors[0].message);
    } else {
      alert('code redeemed successfully: ' + res.data.redeem.message);
    }
  };
  