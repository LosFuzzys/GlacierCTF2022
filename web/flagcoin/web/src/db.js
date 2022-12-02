const mongoose = require('mongoose');
const crypto = require("crypto");


const VoucherSchema = new mongoose.Schema({
  code: { type: String, maxLength: 200 },
  message: { type: String, maxLength: 200 },
  coins: Number
});

const UserSchema = new mongoose.Schema({
  username: { type: String, unique: true, maxLength: 20 },
  password: { type: String, maxLength: 20 },
  coins: Number
});

const User = mongoose.model('user', UserSchema);
const Voucher = mongoose.model('voucher', VoucherSchema);

module.exports = {
  User: User,
  Voucher: Voucher,
};

(() => {
  Voucher.countDocuments((err, count) => {
    console.log(count);
    if (count == 0) {
      let v = new Voucher({
        code: process.env.VOUCHER_CODE || ''+crypto.randomInt(0xffffffffffff),
        message: process.env.FLAG2,
        coins: 100
      });
      v.save();
    }
  })
})();
