# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended to check this file into your version control system.

ActiveRecord::Schema.define(:version => 20110106180225) do

  create_table "groups", :force => true do |t|
    t.string   "name"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "measured_datas", :force => true do |t|
    t.float    "messdaten_float"
    t.integer  "messdaten_int"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "sensor_types", :force => true do |t|
    t.string   "name"
    t.string   "unit"
    t.string   "interface"
    t.string   "formula"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "sensors", :force => true do |t|
    t.string   "port"
    t.string   "station"
    t.string   "typ"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "stations", :force => true do |t|
    t.string   "sensor"
    t.boolean  "active"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

end
