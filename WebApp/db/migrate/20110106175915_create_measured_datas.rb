class CreateMeasuredDatas < ActiveRecord::Migration
  def self.up
    create_table :measured_datas do |t|
		t.float :messdaten_float
		t.integer :messdaten_int

		t.timestamps
    end
  end

  def self.down
    drop_table :measured_datas
  end
end
