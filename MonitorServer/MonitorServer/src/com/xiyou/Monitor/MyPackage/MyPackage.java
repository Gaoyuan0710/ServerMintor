package com.xiyou.Monitor.MyPackage;

// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ServerInfo.proto
public final class MyPackage {
    private MyPackage() {
    }

    public static void registerAllExtensions(
            com.google.protobuf.ExtensionRegistry registry) {
    }

    public interface InfoPackageOrBuilder
            extends com.google.protobuf.MessageOrBuilder {

        // required int32 infoTypes = 1;

        /**
         * <code>required int32 infoTypes = 1;</code>
         */
        boolean hasInfoTypes();

        /**
         * <code>required int32 infoTypes = 1;</code>
         */
        int getInfoTypes();

        // required int32 infoLen = 2;

        /**
         * <code>required int32 infoLen = 2;</code>
         */
        boolean hasInfoLen();

        /**
         * <code>required int32 infoLen = 2;</code>
         */
        int getInfoLen();

        // required string infoData = 3;

        /**
         * <code>required string infoData = 3;</code>
         */
        boolean hasInfoData();

        /**
         * <code>required string infoData = 3;</code>
         */
        java.lang.String getInfoData();

        /**
         * <code>required string infoData = 3;</code>
         */
        com.google.protobuf.ByteString
        getInfoDataBytes();
    }

    /**
     * Protobuf type {@code ServerInfo.InfoPackage}
     */
    public static final class InfoPackage extends
            com.google.protobuf.GeneratedMessage
            implements InfoPackageOrBuilder {
        // Use InfoPackage.newBuilder() to construct.
        private InfoPackage(com.google.protobuf.GeneratedMessage.Builder<?> builder) {
            super(builder);
            this.unknownFields = builder.getUnknownFields();
        }

        private InfoPackage(boolean noInit) {
            this.unknownFields = com.google.protobuf.UnknownFieldSet.getDefaultInstance();
        }

        private static final InfoPackage defaultInstance;

        public static InfoPackage getDefaultInstance() {
            return defaultInstance;
        }

        public InfoPackage getDefaultInstanceForType() {
            return defaultInstance;
        }

        private final com.google.protobuf.UnknownFieldSet unknownFields;

        @java.lang.Override
        public final com.google.protobuf.UnknownFieldSet
        getUnknownFields() {
            return this.unknownFields;
        }

        private InfoPackage(
                com.google.protobuf.CodedInputStream input,
                com.google.protobuf.ExtensionRegistryLite extensionRegistry)
                throws com.google.protobuf.InvalidProtocolBufferException {
            initFields();
            int mutable_bitField0_ = 0;
            com.google.protobuf.UnknownFieldSet.Builder unknownFields =
                    com.google.protobuf.UnknownFieldSet.newBuilder();
            try {
                boolean done = false;
                while (!done) {
                    int tag = input.readTag();
                    switch (tag) {
                        case 0:
                            done = true;
                            break;
                        default: {
                            if (!parseUnknownField(input, unknownFields,
                                    extensionRegistry, tag)) {
                                done = true;
                            }
                            break;
                        }
                        case 8: {
                            bitField0_ |= 0x00000001;
                            infoTypes_ = input.readInt32();
                            break;
                        }
                        case 16: {
                            bitField0_ |= 0x00000002;
                            infoLen_ = input.readInt32();
                            break;
                        }
                        case 26: {
                            bitField0_ |= 0x00000004;
                            infoData_ = input.readBytes();
                            break;
                        }
                    }
                }
            } catch (com.google.protobuf.InvalidProtocolBufferException e) {
                throw e.setUnfinishedMessage(this);
            } catch (java.io.IOException e) {
                throw new com.google.protobuf.InvalidProtocolBufferException(
                        e.getMessage()).setUnfinishedMessage(this);
            } finally {
                this.unknownFields = unknownFields.build();
                makeExtensionsImmutable();
            }
        }

        public static final com.google.protobuf.Descriptors.Descriptor
        getDescriptor() {
            return com.xiyou.Monitor.MyPackage.MyPackage.internal_static_ServerInfo_InfoPackage_descriptor;
        }

        protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
        internalGetFieldAccessorTable() {
            return com.xiyou.Monitor.MyPackage.MyPackage.internal_static_ServerInfo_InfoPackage_fieldAccessorTable
                    .ensureFieldAccessorsInitialized(
                            com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage.class, com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage.Builder.class);
        }

        public static com.google.protobuf.Parser<InfoPackage> PARSER =
                new com.google.protobuf.AbstractParser<InfoPackage>() {
                    public InfoPackage parsePartialFrom(
                            com.google.protobuf.CodedInputStream input,
                            com.google.protobuf.ExtensionRegistryLite extensionRegistry)
                            throws com.google.protobuf.InvalidProtocolBufferException {
                        return new InfoPackage(input, extensionRegistry);
                    }
                };

        @java.lang.Override
        public com.google.protobuf.Parser<InfoPackage> getParserForType() {
            return PARSER;
        }

        private int bitField0_;
        // required int32 infoTypes = 1;
        public static final int INFOTYPES_FIELD_NUMBER = 1;
        private int infoTypes_;

        /**
         * <code>required int32 infoTypes = 1;</code>
         */
        public boolean hasInfoTypes() {
            return ((bitField0_ & 0x00000001) == 0x00000001);
        }

        /**
         * <code>required int32 infoTypes = 1;</code>
         */
        public int getInfoTypes() {
            return infoTypes_;
        }

        // required int32 infoLen = 2;
        public static final int INFOLEN_FIELD_NUMBER = 2;
        private int infoLen_;

        /**
         * <code>required int32 infoLen = 2;</code>
         */
        public boolean hasInfoLen() {
            return ((bitField0_ & 0x00000002) == 0x00000002);
        }

        /**
         * <code>required int32 infoLen = 2;</code>
         */
        public int getInfoLen() {
            return infoLen_;
        }

        // required string infoData = 3;
        public static final int INFODATA_FIELD_NUMBER = 3;
        private java.lang.Object infoData_;

        /**
         * <code>required string infoData = 3;</code>
         */
        public boolean hasInfoData() {
            return ((bitField0_ & 0x00000004) == 0x00000004);
        }

        /**
         * <code>required string infoData = 3;</code>
         */
        public java.lang.String getInfoData() {
            java.lang.Object ref = infoData_;
            if (ref instanceof java.lang.String) {
                return (java.lang.String) ref;
            } else {
                com.google.protobuf.ByteString bs =
                        (com.google.protobuf.ByteString) ref;
                java.lang.String s = bs.toStringUtf8();
                if (bs.isValidUtf8()) {
                    infoData_ = s;
                }
                return s;
            }
        }

        /**
         * <code>required string infoData = 3;</code>
         */
        public com.google.protobuf.ByteString
        getInfoDataBytes() {
            java.lang.Object ref = infoData_;
            if (ref instanceof java.lang.String) {
                com.google.protobuf.ByteString b =
                        com.google.protobuf.ByteString.copyFromUtf8(
                                (java.lang.String) ref);
                infoData_ = b;
                return b;
            } else {
                return (com.google.protobuf.ByteString) ref;
            }
        }

        private void initFields() {
            infoTypes_ = 0;
            infoLen_ = 0;
            infoData_ = "";
        }

        private byte memoizedIsInitialized = -1;

        public final boolean isInitialized() {
            byte isInitialized = memoizedIsInitialized;
            if (isInitialized != -1) return isInitialized == 1;

            if (!hasInfoTypes()) {
                memoizedIsInitialized = 0;
                return false;
            }
            if (!hasInfoLen()) {
                memoizedIsInitialized = 0;
                return false;
            }
            if (!hasInfoData()) {
                memoizedIsInitialized = 0;
                return false;
            }
            memoizedIsInitialized = 1;
            return true;
        }

        public void writeTo(com.google.protobuf.CodedOutputStream output)
                throws java.io.IOException {
            getSerializedSize();
            if (((bitField0_ & 0x00000001) == 0x00000001)) {
                output.writeInt32(1, infoTypes_);
            }
            if (((bitField0_ & 0x00000002) == 0x00000002)) {
                output.writeInt32(2, infoLen_);
            }
            if (((bitField0_ & 0x00000004) == 0x00000004)) {
                output.writeBytes(3, getInfoDataBytes());
            }
            getUnknownFields().writeTo(output);
        }

        private int memoizedSerializedSize = -1;

        public int getSerializedSize() {
            int size = memoizedSerializedSize;
            if (size != -1) return size;

            size = 0;
            if (((bitField0_ & 0x00000001) == 0x00000001)) {
                size += com.google.protobuf.CodedOutputStream
                        .computeInt32Size(1, infoTypes_);
            }
            if (((bitField0_ & 0x00000002) == 0x00000002)) {
                size += com.google.protobuf.CodedOutputStream
                        .computeInt32Size(2, infoLen_);
            }
            if (((bitField0_ & 0x00000004) == 0x00000004)) {
                size += com.google.protobuf.CodedOutputStream
                        .computeBytesSize(3, getInfoDataBytes());
            }
            size += getUnknownFields().getSerializedSize();
            memoizedSerializedSize = size;
            return size;
        }

        private static final long serialVersionUID = 0L;

        @java.lang.Override
        protected java.lang.Object writeReplace()
                throws java.io.ObjectStreamException {
            return super.writeReplace();
        }

        public static com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage parseFrom(
                com.google.protobuf.ByteString data)
                throws com.google.protobuf.InvalidProtocolBufferException {
            return PARSER.parseFrom(data);
        }

        public static com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage parseFrom(
                com.google.protobuf.ByteString data,
                com.google.protobuf.ExtensionRegistryLite extensionRegistry)
                throws com.google.protobuf.InvalidProtocolBufferException {
            return PARSER.parseFrom(data, extensionRegistry);
        }

        public static com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage parseFrom(byte[] data)
                throws com.google.protobuf.InvalidProtocolBufferException {
            return PARSER.parseFrom(data);
        }

        public static com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage parseFrom(
                byte[] data,
                com.google.protobuf.ExtensionRegistryLite extensionRegistry)
                throws com.google.protobuf.InvalidProtocolBufferException {
            return PARSER.parseFrom(data, extensionRegistry);
        }

        public static com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage parseFrom(java.io.InputStream input)
                throws java.io.IOException {
            return PARSER.parseFrom(input);
        }

        public static com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage parseFrom(
                java.io.InputStream input,
                com.google.protobuf.ExtensionRegistryLite extensionRegistry)
                throws java.io.IOException {
            return PARSER.parseFrom(input, extensionRegistry);
        }

        public static com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage parseDelimitedFrom(java.io.InputStream input)
                throws java.io.IOException {
            return PARSER.parseDelimitedFrom(input);
        }

        public static com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage parseDelimitedFrom(
                java.io.InputStream input,
                com.google.protobuf.ExtensionRegistryLite extensionRegistry)
                throws java.io.IOException {
            return PARSER.parseDelimitedFrom(input, extensionRegistry);
        }

        public static com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage parseFrom(
                com.google.protobuf.CodedInputStream input)
                throws java.io.IOException {
            return PARSER.parseFrom(input);
        }

        public static com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage parseFrom(
                com.google.protobuf.CodedInputStream input,
                com.google.protobuf.ExtensionRegistryLite extensionRegistry)
                throws java.io.IOException {
            return PARSER.parseFrom(input, extensionRegistry);
        }

        public static Builder newBuilder() {
            return Builder.create();
        }

        public Builder newBuilderForType() {
            return newBuilder();
        }

        public static Builder newBuilder(com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage prototype) {
            return newBuilder().mergeFrom(prototype);
        }

        public Builder toBuilder() {
            return newBuilder(this);
        }

        @java.lang.Override
        protected Builder newBuilderForType(
                com.google.protobuf.GeneratedMessage.BuilderParent parent) {
            Builder builder = new Builder(parent);
            return builder;
        }

        /**
         * Protobuf type {@code ServerInfo.InfoPackage}
         */
        public static final class Builder extends
                com.google.protobuf.GeneratedMessage.Builder<Builder>
                implements com.xiyou.Monitor.MyPackage.MyPackage.InfoPackageOrBuilder {
            public static final com.google.protobuf.Descriptors.Descriptor
            getDescriptor() {
                return com.xiyou.Monitor.MyPackage.MyPackage.internal_static_ServerInfo_InfoPackage_descriptor;
            }

            protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
            internalGetFieldAccessorTable() {
                return com.xiyou.Monitor.MyPackage.MyPackage.internal_static_ServerInfo_InfoPackage_fieldAccessorTable
                        .ensureFieldAccessorsInitialized(
                                com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage.class, com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage.Builder.class);
            }

            // Construct using com.mypackage.MyPackage.InfoPackage.newBuilder()
            private Builder() {
                maybeForceBuilderInitialization();
            }

            private Builder(
                    com.google.protobuf.GeneratedMessage.BuilderParent parent) {
                super(parent);
                maybeForceBuilderInitialization();
            }

            private void maybeForceBuilderInitialization() {
                if (com.google.protobuf.GeneratedMessage.alwaysUseFieldBuilders) {
                }
            }

            private static Builder create() {
                return new Builder();
            }

            public Builder clear() {
                super.clear();
                infoTypes_ = 0;
                bitField0_ = (bitField0_ & ~0x00000001);
                infoLen_ = 0;
                bitField0_ = (bitField0_ & ~0x00000002);
                infoData_ = "";
                bitField0_ = (bitField0_ & ~0x00000004);
                return this;
            }

            public Builder clone() {
                return create().mergeFrom(buildPartial());
            }

            public com.google.protobuf.Descriptors.Descriptor
            getDescriptorForType() {
                return com.xiyou.Monitor.MyPackage.MyPackage.internal_static_ServerInfo_InfoPackage_descriptor;
            }

            public com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage getDefaultInstanceForType() {
                return com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage.getDefaultInstance();
            }

            public com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage build() {
                com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage result = buildPartial();
                if (!result.isInitialized()) {
                    throw newUninitializedMessageException(result);
                }
                return result;
            }

            public com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage buildPartial() {
                com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage result = new com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage(this);
                int from_bitField0_ = bitField0_;
                int to_bitField0_ = 0;
                if (((from_bitField0_ & 0x00000001) == 0x00000001)) {
                    to_bitField0_ |= 0x00000001;
                }
                result.infoTypes_ = infoTypes_;
                if (((from_bitField0_ & 0x00000002) == 0x00000002)) {
                    to_bitField0_ |= 0x00000002;
                }
                result.infoLen_ = infoLen_;
                if (((from_bitField0_ & 0x00000004) == 0x00000004)) {
                    to_bitField0_ |= 0x00000004;
                }
                result.infoData_ = infoData_;
                result.bitField0_ = to_bitField0_;
                onBuilt();
                return result;
            }

            public Builder mergeFrom(com.google.protobuf.Message other) {
                if (other instanceof com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage) {
                    return mergeFrom((com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage) other);
                } else {
                    super.mergeFrom(other);
                    return this;
                }
            }

            public Builder mergeFrom(com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage other) {
                if (other == com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage.getDefaultInstance()) return this;
                if (other.hasInfoTypes()) {
                    setInfoTypes(other.getInfoTypes());
                }
                if (other.hasInfoLen()) {
                    setInfoLen(other.getInfoLen());
                }
                if (other.hasInfoData()) {
                    bitField0_ |= 0x00000004;
                    infoData_ = other.infoData_;
                    onChanged();
                }
                this.mergeUnknownFields(other.getUnknownFields());
                return this;
            }

            public final boolean isInitialized() {
                if (!hasInfoTypes()) {

                    return false;
                }
                if (!hasInfoLen()) {

                    return false;
                }
                if (!hasInfoData()) {

                    return false;
                }
                return true;
            }

            public Builder mergeFrom(
                    com.google.protobuf.CodedInputStream input,
                    com.google.protobuf.ExtensionRegistryLite extensionRegistry)
                    throws java.io.IOException {
                com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage parsedMessage = null;
                try {
                    parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
                } catch (com.google.protobuf.InvalidProtocolBufferException e) {
                    parsedMessage = (com.xiyou.Monitor.MyPackage.MyPackage.InfoPackage) e.getUnfinishedMessage();
                    throw e;
                } finally {
                    if (parsedMessage != null) {
                        mergeFrom(parsedMessage);
                    }
                }
                return this;
            }

            private int bitField0_;

            // required int32 infoTypes = 1;
            private int infoTypes_;

            /**
             * <code>required int32 infoTypes = 1;</code>
             */
            public boolean hasInfoTypes() {
                return ((bitField0_ & 0x00000001) == 0x00000001);
            }

            /**
             * <code>required int32 infoTypes = 1;</code>
             */
            public int getInfoTypes() {
                return infoTypes_;
            }

            /**
             * <code>required int32 infoTypes = 1;</code>
             */
            public Builder setInfoTypes(int value) {
                bitField0_ |= 0x00000001;
                infoTypes_ = value;
                onChanged();
                return this;
            }

            /**
             * <code>required int32 infoTypes = 1;</code>
             */
            public Builder clearInfoTypes() {
                bitField0_ = (bitField0_ & ~0x00000001);
                infoTypes_ = 0;
                onChanged();
                return this;
            }

            // required int32 infoLen = 2;
            private int infoLen_;

            /**
             * <code>required int32 infoLen = 2;</code>
             */
            public boolean hasInfoLen() {
                return ((bitField0_ & 0x00000002) == 0x00000002);
            }

            /**
             * <code>required int32 infoLen = 2;</code>
             */
            public int getInfoLen() {
                return infoLen_;
            }

            /**
             * <code>required int32 infoLen = 2;</code>
             */
            public Builder setInfoLen(int value) {
                bitField0_ |= 0x00000002;
                infoLen_ = value;
                onChanged();
                return this;
            }

            /**
             * <code>required int32 infoLen = 2;</code>
             */
            public Builder clearInfoLen() {
                bitField0_ = (bitField0_ & ~0x00000002);
                infoLen_ = 0;
                onChanged();
                return this;
            }

            // required string infoData = 3;
            private java.lang.Object infoData_ = "";

            /**
             * <code>required string infoData = 3;</code>
             */
            public boolean hasInfoData() {
                return ((bitField0_ & 0x00000004) == 0x00000004);
            }

            /**
             * <code>required string infoData = 3;</code>
             */
            public java.lang.String getInfoData() {
                java.lang.Object ref = infoData_;
                if (!(ref instanceof java.lang.String)) {
                    java.lang.String s = ((com.google.protobuf.ByteString) ref)
                            .toStringUtf8();
                    infoData_ = s;
                    return s;
                } else {
                    return (java.lang.String) ref;
                }
            }

            /**
             * <code>required string infoData = 3;</code>
             */
            public com.google.protobuf.ByteString
            getInfoDataBytes() {
                java.lang.Object ref = infoData_;
                if (ref instanceof String) {
                    com.google.protobuf.ByteString b =
                            com.google.protobuf.ByteString.copyFromUtf8(
                                    (java.lang.String) ref);
                    infoData_ = b;
                    return b;
                } else {
                    return (com.google.protobuf.ByteString) ref;
                }
            }

            /**
             * <code>required string infoData = 3;</code>
             */
            public Builder setInfoData(
                    java.lang.String value) {
                if (value == null) {
                    throw new NullPointerException();
                }
                bitField0_ |= 0x00000004;
                infoData_ = value;
                onChanged();
                return this;
            }

            /**
             * <code>required string infoData = 3;</code>
             */
            public Builder clearInfoData() {
                bitField0_ = (bitField0_ & ~0x00000004);
                infoData_ = getDefaultInstance().getInfoData();
                onChanged();
                return this;
            }

            /**
             * <code>required string infoData = 3;</code>
             */
            public Builder setInfoDataBytes(
                    com.google.protobuf.ByteString value) {
                if (value == null) {
                    throw new NullPointerException();
                }
                bitField0_ |= 0x00000004;
                infoData_ = value;
                onChanged();
                return this;
            }

            // @@protoc_insertion_point(builder_scope:ServerInfo.InfoPackage)
        }

        static {
            defaultInstance = new InfoPackage(true);
            defaultInstance.initFields();
        }

        // @@protoc_insertion_point(class_scope:ServerInfo.InfoPackage)
    }

    private static com.google.protobuf.Descriptors.Descriptor
            internal_static_ServerInfo_InfoPackage_descriptor;
    private static
    com.google.protobuf.GeneratedMessage.FieldAccessorTable
            internal_static_ServerInfo_InfoPackage_fieldAccessorTable;

    public static com.google.protobuf.Descriptors.FileDescriptor
    getDescriptor() {
        return descriptor;
    }

    private static com.google.protobuf.Descriptors.FileDescriptor
            descriptor;

    static {
        java.lang.String[] descriptorData = {
                "\n\020ServerInfo.proto\022\nServerInfo\"C\n\013InfoPa" +
                        "ckage\022\021\n\tinfoTypes\030\001 \002(\005\022\017\n\007infoLen\030\002 \002(" +
                        "\005\022\020\n\010infoData\030\003 \002(\tB\032\n\rcom.mypackageB\tMy" +
                        "Package"
        };
        com.google.protobuf.Descriptors.FileDescriptor.InternalDescriptorAssigner assigner =
                new com.google.protobuf.Descriptors.FileDescriptor.InternalDescriptorAssigner() {
                    public com.google.protobuf.ExtensionRegistry assignDescriptors(
                            com.google.protobuf.Descriptors.FileDescriptor root) {
                        descriptor = root;
                        internal_static_ServerInfo_InfoPackage_descriptor =
                                getDescriptor().getMessageTypes().get(0);
                        internal_static_ServerInfo_InfoPackage_fieldAccessorTable = new
                                com.google.protobuf.GeneratedMessage.FieldAccessorTable(
                                internal_static_ServerInfo_InfoPackage_descriptor,
                                new java.lang.String[]{"InfoTypes", "InfoLen", "InfoData",});
                        return null;
                    }
                };
        com.google.protobuf.Descriptors.FileDescriptor
                .internalBuildGeneratedFileFrom(descriptorData,
                        new com.google.protobuf.Descriptors.FileDescriptor[]{
                        }, assigner);
    }

    // @@protoc_insertion_point(outer_class_scope)
}
