const path = require('path')
const grpc = require('@grpc/grpc-js')
const portoLoader = require('@grpc/proto-loader')

const PROTO_PATH = path.join(__dirname, 'message.proto')
const packageDefinition = portoLoader.loadSync(PROTO_PATH,{KeepCase:true, longs:String,
    enums:String, defaults:true, oneofs:true
})

const protoDescriptor = grpc.loadPackageDefinition(packageDefinition)

const message_proto = protoDescriptor.message

module.exports = message_proto